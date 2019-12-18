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
struct store_ctx {int /*<<< orphan*/ * f; int /*<<< orphan*/  format; } ;
struct ks_file {int /*<<< orphan*/  certs; int /*<<< orphan*/  format; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct store_ctx*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  rk_cloexec_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_func ; 

__attribute__((used)) static int
file_store(hx509_context context,
	   hx509_certs certs, void *data, int flags, hx509_lock lock)
{
    struct ks_file *ksf = data;
    struct store_ctx sc;
    int ret;

    sc.f = fopen(ksf->fn, "w");
    if (sc.f == NULL) {
	hx509_set_error_string(context, 0, ENOENT,
			       "Failed to open file %s for writing");
	return ENOENT;
    }
    rk_cloexec_file(sc.f);
    sc.format = ksf->format;

    ret = hx509_certs_iter_f(context, ksf->certs, store_func, &sc);
    fclose(sc.f);
    return ret;
}