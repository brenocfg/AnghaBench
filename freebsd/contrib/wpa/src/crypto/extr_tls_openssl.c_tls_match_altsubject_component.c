#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ stack_index_t ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {TYPE_1__* ia5; } ;
struct TYPE_7__ {int type; TYPE_2__ d; } ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_3__ GENERAL_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_NAME_free ; 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 void* X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (char const*,scalar_t__,size_t) ; 
 size_t os_strlen (char*) ; 
 scalar_t__ sk_GENERAL_NAME_num (void*) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_pop_free (void*,int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_GENERAL_NAME_value (void*,scalar_t__) ; 

__attribute__((used)) static int tls_match_altsubject_component(X509 *cert, int type,
					  const char *value, size_t len)
{
	GENERAL_NAME *gen;
	void *ext;
	int found = 0;
	stack_index_t i;

	ext = X509_get_ext_d2i(cert, NID_subject_alt_name, NULL, NULL);

	for (i = 0; ext && i < sk_GENERAL_NAME_num(ext); i++) {
		gen = sk_GENERAL_NAME_value(ext, i);
		if (gen->type != type)
			continue;
		if (os_strlen((char *) gen->d.ia5->data) == len &&
		    os_memcmp(value, gen->d.ia5->data, len) == 0)
			found++;
	}

	sk_GENERAL_NAME_pop_free(ext, GENERAL_NAME_free);

	return found;
}