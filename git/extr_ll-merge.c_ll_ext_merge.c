#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp ;
struct strbuf_expand_dict_entry {char* placeholder; char* value; } ;
struct strbuf {char* buf; } ;
struct stat {int /*<<< orphan*/  st_size; } ;
struct ll_merge_options {int dummy; } ;
struct ll_merge_driver {int /*<<< orphan*/ * cmdline; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ mmbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RUN_USING_SHELL ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (struct ll_merge_options const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  create_temp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_in_full (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_expand (struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct strbuf_expand_dict_entry**) ; 
 int /*<<< orphan*/  strbuf_expand_dict_cb ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unlink_or_warn (char*) ; 
 int /*<<< orphan*/ * xmallocz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int) ; 

__attribute__((used)) static int ll_ext_merge(const struct ll_merge_driver *fn,
			mmbuffer_t *result,
			const char *path,
			mmfile_t *orig, const char *orig_name,
			mmfile_t *src1, const char *name1,
			mmfile_t *src2, const char *name2,
			const struct ll_merge_options *opts,
			int marker_size)
{
	char temp[4][50];
	struct strbuf cmd = STRBUF_INIT;
	struct strbuf_expand_dict_entry dict[6];
	struct strbuf path_sq = STRBUF_INIT;
	const char *args[] = { NULL, NULL };
	int status, fd, i;
	struct stat st;
	assert(opts);

	sq_quote_buf(&path_sq, path);
	dict[0].placeholder = "O"; dict[0].value = temp[0];
	dict[1].placeholder = "A"; dict[1].value = temp[1];
	dict[2].placeholder = "B"; dict[2].value = temp[2];
	dict[3].placeholder = "L"; dict[3].value = temp[3];
	dict[4].placeholder = "P"; dict[4].value = path_sq.buf;
	dict[5].placeholder = NULL; dict[5].value = NULL;

	if (fn->cmdline == NULL)
		die("custom merge driver %s lacks command line.", fn->name);

	result->ptr = NULL;
	result->size = 0;
	create_temp(orig, temp[0], sizeof(temp[0]));
	create_temp(src1, temp[1], sizeof(temp[1]));
	create_temp(src2, temp[2], sizeof(temp[2]));
	xsnprintf(temp[3], sizeof(temp[3]), "%d", marker_size);

	strbuf_expand(&cmd, fn->cmdline, strbuf_expand_dict_cb, &dict);

	args[0] = cmd.buf;
	status = run_command_v_opt(args, RUN_USING_SHELL);
	fd = open(temp[1], O_RDONLY);
	if (fd < 0)
		goto bad;
	if (fstat(fd, &st))
		goto close_bad;
	result->size = st.st_size;
	result->ptr = xmallocz(result->size);
	if (read_in_full(fd, result->ptr, result->size) != result->size) {
		FREE_AND_NULL(result->ptr);
		result->size = 0;
	}
 close_bad:
	close(fd);
 bad:
	for (i = 0; i < 3; i++)
		unlink_or_warn(temp[i]);
	strbuf_release(&cmd);
	strbuf_release(&path_sq);
	return status;
}