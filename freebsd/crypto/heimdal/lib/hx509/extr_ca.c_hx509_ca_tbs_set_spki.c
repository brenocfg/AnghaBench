#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_ca_tbs ;
struct TYPE_4__ {int key; } ;
struct TYPE_5__ {TYPE_1__ flags; int /*<<< orphan*/  spki; } ;
typedef  int /*<<< orphan*/  SubjectPublicKeyInfo ;

/* Variables and functions */
 int copy_SubjectPublicKeyInfo (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_SubjectPublicKeyInfo (int /*<<< orphan*/ *) ; 

int
hx509_ca_tbs_set_spki(hx509_context context,
		      hx509_ca_tbs tbs,
		      const SubjectPublicKeyInfo *spki)
{
    int ret;
    free_SubjectPublicKeyInfo(&tbs->spki);
    ret = copy_SubjectPublicKeyInfo(spki, &tbs->spki);
    tbs->flags.key = !ret;
    return ret;
}