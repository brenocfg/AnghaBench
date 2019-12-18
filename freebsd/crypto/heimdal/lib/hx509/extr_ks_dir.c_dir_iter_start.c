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
struct dircursor {int /*<<< orphan*/ * iter; int /*<<< orphan*/ * certs; int /*<<< orphan*/ * dir; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int ENOMEM ; 
 struct dircursor* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct dircursor*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (void*) ; 
 int /*<<< orphan*/  rk_cloexec_dir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dir_iter_start(hx509_context context,
	       hx509_certs certs, void *data, void **cursor)
{
    struct dircursor *d;

    *cursor = NULL;

    d = calloc(1, sizeof(*d));
    if (d == NULL) {
	hx509_clear_error_string(context);
	return ENOMEM;
    }

    d->dir = opendir(data);
    if (d->dir == NULL) {
	hx509_clear_error_string(context);
	free(d);
	return errno;
    }
    rk_cloexec_dir(d->dir);
    d->certs = NULL;
    d->iter = NULL;

    *cursor = d;
    return 0;
}