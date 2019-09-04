#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {size_t asize; int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct write_data {char* orig_section; char* section; char* orig_name; char* name; char const* value; TYPE_3__ buffered_comment; int /*<<< orphan*/  const* preg; scalar_t__ preg_replaced; scalar_t__ in_section; TYPE_3__* buf; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  reader ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_18__ {int /*<<< orphan*/  ctx; TYPE_1__* file; } ;
typedef  TYPE_2__ git_config_parser ;
typedef  TYPE_3__ git_buf ;
struct TYPE_17__ {int /*<<< orphan*/  path; } ;
struct TYPE_20__ {TYPE_3__ locked_content; scalar_t__ locked; TYPE_1__ file; } ;
typedef  TYPE_4__ diskfile_backend ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_FILE_MODE ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_FILEBUF_HASH_CONTENTS ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strndup (char const*,int) ; 
 int /*<<< orphan*/  git_buf_attach (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 char* git_buf_cstr (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_len (TYPE_3__*) ; 
 int git_buf_puts (TYPE_3__*,char*) ; 
 int git_config_parse (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct write_data*) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int git_futils_readbuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_parse_ctx_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_parse_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  write_on_comment ; 
 int /*<<< orphan*/  write_on_eof ; 
 int /*<<< orphan*/  write_on_section ; 
 int /*<<< orphan*/  write_on_variable ; 

__attribute__((used)) static int config_write(diskfile_backend *cfg, const char *orig_key, const char *key, const regex_t *preg, const char* value)
{
	int result;
	char *orig_section, *section, *orig_name, *name, *ldot;
	git_filebuf file = GIT_FILEBUF_INIT;
	git_buf buf = GIT_BUF_INIT, contents = GIT_BUF_INIT;
	git_config_parser reader;
	struct write_data write_data;

	memset(&reader, 0, sizeof(reader));
	reader.file = &cfg->file;

	if (cfg->locked) {
		result = git_buf_puts(&contents, git_buf_cstr(&cfg->locked_content) == NULL ? "" : git_buf_cstr(&cfg->locked_content));
	} else {
		/* Lock the file */
		if ((result = git_filebuf_open(
			     &file, cfg->file.path, GIT_FILEBUF_HASH_CONTENTS, GIT_CONFIG_FILE_MODE)) < 0) {
			git_buf_dispose(&contents);
			return result;
		}

		/* We need to read in our own config file */
		result = git_futils_readbuffer(&contents, cfg->file.path);
	}

	/* Initialise the reading position */
	if (result == 0 || result == GIT_ENOTFOUND) {
		git_parse_ctx_init(&reader.ctx, contents.ptr, contents.size);
	} else {
		git_filebuf_cleanup(&file);
		return -1; /* OS error when reading the file */
	}

	ldot = strrchr(key, '.');
	name = ldot + 1;
	section = git__strndup(key, ldot - key);
	GIT_ERROR_CHECK_ALLOC(section);

	ldot = strrchr(orig_key, '.');
	orig_name = ldot + 1;
	orig_section = git__strndup(orig_key, ldot - orig_key);
	GIT_ERROR_CHECK_ALLOC(orig_section);

	write_data.buf = &buf;
	git_buf_init(&write_data.buffered_comment, 0);
	write_data.orig_section = orig_section;
	write_data.section = section;
	write_data.in_section = 0;
	write_data.preg_replaced = 0;
	write_data.orig_name = orig_name;
	write_data.name = name;
	write_data.preg = preg;
	write_data.value = value;

	result = git_config_parse(&reader,
		write_on_section,
		write_on_variable,
		write_on_comment,
		write_on_eof,
		&write_data);
	git__free(section);
	git__free(orig_section);
	git_buf_dispose(&write_data.buffered_comment);

	if (result < 0) {
		git_filebuf_cleanup(&file);
		goto done;
	}

	if (cfg->locked) {
		size_t len = buf.asize;
		/* Update our copy with the modified contents */
		git_buf_dispose(&cfg->locked_content);
		git_buf_attach(&cfg->locked_content, git_buf_detach(&buf), len);
	} else {
		git_filebuf_write(&file, git_buf_cstr(&buf), git_buf_len(&buf));
		result = git_filebuf_commit(&file);
	}

done:
	git_buf_dispose(&buf);
	git_buf_dispose(&contents);
	git_parse_ctx_clear(&reader.ctx);
	return result;
}