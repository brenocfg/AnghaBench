#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_request ;
struct TYPE_5__ {int /*<<< orphan*/  san; int /*<<< orphan*/  eku; int /*<<< orphan*/  key; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_ExtKeyUsage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_GeneralNames (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_SubjectPublicKeyInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_free (scalar_t__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_request_free(hx509_request *req)
{
    if ((*req)->name)
	hx509_name_free(&(*req)->name);
    free_SubjectPublicKeyInfo(&(*req)->key);
    free_ExtKeyUsage(&(*req)->eku);
    free_GeneralNames(&(*req)->san);
    memset(*req, 0, sizeof(**req));
    free(*req);
    *req = NULL;
}