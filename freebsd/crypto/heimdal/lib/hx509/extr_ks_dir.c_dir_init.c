#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int stat (char const*,struct stat*) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static int
dir_init(hx509_context context,
	 hx509_certs certs, void **data, int flags,
	 const char *residue, hx509_lock lock)
{
    *data = NULL;

    {
	struct stat sb;
	int ret;

	ret = stat(residue, &sb);
	if (ret == -1) {
	    hx509_set_error_string(context, 0, ENOENT,
				   "No such file %s", residue);
	    return ENOENT;
	}

	if (!S_ISDIR(sb.st_mode)) {
	    hx509_set_error_string(context, 0, ENOTDIR,
				   "%s is not a directory", residue);
	    return ENOTDIR;
	}
    }

    *data = strdup(residue);
    if (*data == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    return 0;
}