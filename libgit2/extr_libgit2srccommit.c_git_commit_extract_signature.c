#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_1__ cached; } ;
typedef  TYPE_2__ git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 scalar_t__ GIT_OBJECT_COMMIT ; 
 scalar_t__ git__prefixcmp (char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_put (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 char* git_odb_object_data (TYPE_2__*) ; 
 int /*<<< orphan*/  git_odb_object_free (TYPE_2__*) ; 
 int git_odb_read (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_commit_extract_signature(git_buf *signature, git_buf *signed_data, git_repository *repo, git_oid *commit_id, const char *field)
{
	git_odb_object *obj;
	git_odb *odb;
	const char *buf;
	const char *h, *eol;
	int error;

	git_buf_clear(signature);
	git_buf_clear(signed_data);

	if (!field)
		field = "gpgsig";

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0)
		return error;

	if ((error = git_odb_read(&obj, odb, commit_id)) < 0)
		return error;

	if (obj->cached.type != GIT_OBJECT_COMMIT) {
		git_error_set(GIT_ERROR_INVALID, "the requested type does not match the type in ODB");
		error = GIT_ENOTFOUND;
		goto cleanup;
	}

	buf = git_odb_object_data(obj);

	while ((h = strchr(buf, '\n')) && h[1] != '\0') {
		h++;
		if (git__prefixcmp(buf, field)) {
			if (git_buf_put(signed_data, buf, h - buf) < 0)
				return -1;

			buf = h;
			continue;
		}

		h = buf;
		h += strlen(field);
		eol = strchr(h, '\n');
		if (h[0] != ' ') {
			buf = h;
			continue;
		}
		if (!eol)
			goto malformed;

		h++; /* skip the SP */

		git_buf_put(signature, h, eol - h);
		if (git_buf_oom(signature))
			goto oom;

		/* If the next line starts with SP, it's multi-line, we must continue */
		while (eol[1] == ' ') {
			git_buf_putc(signature, '\n');
			h = eol + 2;
			eol = strchr(h, '\n');
			if (!eol)
				goto malformed;

			git_buf_put(signature, h, eol - h);
		}

		if (git_buf_oom(signature))
			goto oom;

		error = git_buf_puts(signed_data, eol+1);
		git_odb_object_free(obj);
		return error;
	}

	git_error_set(GIT_ERROR_OBJECT, "this commit is not signed");
	error = GIT_ENOTFOUND;
	goto cleanup;

malformed:
	git_error_set(GIT_ERROR_OBJECT, "malformed header");
	error = -1;
	goto cleanup;
oom:
	git_error_set_oom();
	error = -1;
	goto cleanup;

cleanup:
	git_odb_object_free(obj);
	git_buf_clear(signature);
	git_buf_clear(signed_data);
	return error;
}