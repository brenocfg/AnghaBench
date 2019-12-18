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
struct dirent {int /*<<< orphan*/  d_name; } ;
struct dircursor {int /*<<< orphan*/ * certs; int /*<<< orphan*/ * iter; int /*<<< orphan*/  dir; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;

/* Variables and functions */
 int ENOMEM ; 
 int asprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_certs_end_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int hx509_certs_next_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int hx509_certs_start_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
dir_iter(hx509_context context,
	 hx509_certs certs, void *data, void *iter, hx509_cert *cert)
{
    struct dircursor *d = iter;
    int ret = 0;

    *cert = NULL;

    do {
	struct dirent *dir;
	char *fn;

	if (d->certs) {
	    ret = hx509_certs_next_cert(context, d->certs, d->iter, cert);
	    if (ret) {
		hx509_certs_end_seq(context, d->certs, d->iter);
		d->iter = NULL;
		hx509_certs_free(&d->certs);
		return ret;
	    }
	    if (*cert) {
		ret = 0;
		break;
	    }
	    hx509_certs_end_seq(context, d->certs, d->iter);
	    d->iter = NULL;
	    hx509_certs_free(&d->certs);
	}

	dir = readdir(d->dir);
	if (dir == NULL) {
	    ret = 0;
	    break;
	}
	if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
	    continue;

	if (asprintf(&fn, "FILE:%s/%s", (char *)data, dir->d_name) == -1)
	    return ENOMEM;

	ret = hx509_certs_init(context, fn, 0, NULL, &d->certs);
	if (ret == 0) {

	    ret = hx509_certs_start_seq(context, d->certs, &d->iter);
	    if (ret)
	    hx509_certs_free(&d->certs);
	}
	/* ignore errors */
	if (ret) {
	    d->certs = NULL;
	    ret = 0;
	}

	free(fn);
    } while(ret == 0);

    return ret;
}