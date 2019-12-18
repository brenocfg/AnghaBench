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
struct dircursor {int /*<<< orphan*/  dir; scalar_t__ certs; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct dircursor*) ; 
 int /*<<< orphan*/  hx509_certs_end_seq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_free (scalar_t__*) ; 

__attribute__((used)) static int
dir_iter_end(hx509_context context,
	     hx509_certs certs,
	     void *data,
	     void *cursor)
{
    struct dircursor *d = cursor;

    if (d->certs) {
	hx509_certs_end_seq(context, d->certs, d->iter);
	d->iter = NULL;
	hx509_certs_free(&d->certs);
    }
    closedir(d->dir);
    free(d);
    return 0;
}