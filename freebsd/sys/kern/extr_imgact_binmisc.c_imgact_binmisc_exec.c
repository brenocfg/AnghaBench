#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sbuf {int dummy; } ;
struct image_params {char* image_header; int interpreted; char* interpreter_name; TYPE_3__* args; } ;
struct TYPE_4__ {size_t ibe_interp_length; char* ibe_interpreter; scalar_t__ ibe_interp_argcnt; } ;
typedef  TYPE_1__ imgact_binmisc_entry_t ;
struct TYPE_5__ {char* fname; char* begin_argv; int /*<<< orphan*/  argc; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOEXEC ; 
 int IMGACT_BINMISC ; 
#define  ISM_OLD_ARGV0 129 
#define  ISM_POUND 128 
 char* KMOD_NAME ; 
 int exec_args_adjust_args (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* imgact_binmisc_find_interpreter (char const*) ; 
 int /*<<< orphan*/  interp_list_sx ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*,char) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imgact_binmisc_exec(struct image_params *imgp)
{
	const char *image_header = imgp->image_header;
	const char *fname = NULL;
	int error = 0;
	size_t offset, l;
	imgact_binmisc_entry_t *ibe;
	struct sbuf *sname;
	char *s, *d;

	/* Do we have an interpreter for the given image header? */
	sx_slock(&interp_list_sx);
	if ((ibe = imgact_binmisc_find_interpreter(image_header)) == NULL) {
		sx_sunlock(&interp_list_sx);
		return (-1);
	}

	/* No interpreter nesting allowed. */
	if (imgp->interpreted & IMGACT_BINMISC) {
		sx_sunlock(&interp_list_sx);
		return (ENOEXEC);
	}

	imgp->interpreted |= IMGACT_BINMISC;

	if (imgp->args->fname != NULL) {
		fname = imgp->args->fname;
		sname = NULL;
	} else {
		/* Use the fdescfs(5) path for fexecve(2). */
		sname = sbuf_new_auto();
		sbuf_printf(sname, "/dev/fd/%d", imgp->args->fd);
		sbuf_finish(sname);
		fname = sbuf_data(sname);
	}


	/*
	 * We need to "push" the interpreter in the arg[] list.  To do this,
	 * we first shift all the other values in the `begin_argv' area to
	 * provide the exact amount of room for the values added.  Set up
	 * `offset' as the number of bytes to be added to the `begin_argv'
	 * area.
	 */
	offset = ibe->ibe_interp_length;

	/* Adjust the offset for #'s. */
	s = ibe->ibe_interpreter;
	while (1) {
		s = strchr(s, '#');
		if (!s)
			break;

		s++;
		switch(*s) {
		case ISM_POUND:
			/* "##" -> "#": reduce offset by one. */
			offset--;
			break;

		case ISM_OLD_ARGV0:
			/* "#a" -> (old argv0): increase offset to fit fname */
			offset += strlen(fname) - 2;
			break;

		default:
			/* Hmm... This shouldn't happen. */
			sx_sunlock(&interp_list_sx);
			printf("%s: Unknown macro #%c sequence in "
			    "interpreter string\n", KMOD_NAME, *(s + 1));
			error = EINVAL;
			goto done;
		}
		s++;
	}

	/* Make room for the interpreter */
	error = exec_args_adjust_args(imgp->args, 0, offset);
	if (error != 0) {
		sx_sunlock(&interp_list_sx);
		goto done;
	}

	/* Add the new argument(s) in the count. */
	imgp->args->argc += ibe->ibe_interp_argcnt;

	/*
	 * The original arg[] list has been shifted appropriately.  Copy in
	 * the interpreter path.
	 */
	s = ibe->ibe_interpreter;
	d = imgp->args->begin_argv;
	while(*s != '\0') {
		switch (*s) {
		case '#':
			/* Handle "#" in interpreter string. */
			s++;
			switch(*s) {
			case ISM_POUND:
				/* "##": Replace with a single '#' */
				*d++ = '#';
				break;

			case ISM_OLD_ARGV0:
				/* "#a": Replace with old arg0 (fname). */
				if ((l = strlen(fname)) != 0) {
					memcpy(d, fname, l);
					d += l;
				}
				break;

			default:
				/* Shouldn't happen but skip it if it does. */
				break;
			}
			break;

		case ' ':
			/* Replace space with NUL to separate arguments. */
			*d++ = '\0';
			break;

		default:
			*d++ = *s;
			break;
		}
		s++;
	}
	*d = '\0';
	sx_sunlock(&interp_list_sx);

	if (!error)
		imgp->interpreter_name = imgp->args->begin_argv;


done:
	if (sname)
		sbuf_delete(sname);
	return (error);
}