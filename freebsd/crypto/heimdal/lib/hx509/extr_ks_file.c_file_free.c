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
struct ks_file {struct ks_file* fn; int /*<<< orphan*/  certs; } ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ks_file*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
file_free(hx509_certs certs, void *data)
{
    struct ks_file *ksf = data;
    hx509_certs_free(&ksf->certs);
    free(ksf->fn);
    free(ksf);
    return 0;
}