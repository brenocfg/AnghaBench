#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_signing_algorithm ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct TYPE_8__ {TYPE_1__ _key; } ;
typedef  TYPE_2__ ldns_key ;
typedef  scalar_t__ ldns_algorithm ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_load_private_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LDNS_STATUS_ENGINE_KEY_NOT_LOADED ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  UI_OpenSSL () ; 
 int /*<<< orphan*/  ldns_key_free (TYPE_2__*) ; 
 TYPE_2__* ldns_key_new () ; 
 int /*<<< orphan*/  ldns_key_set_algorithm (TYPE_2__*,int /*<<< orphan*/ ) ; 

ldns_status
ldns_key_new_frm_engine(ldns_key **key, ENGINE *e, char *key_id, ldns_algorithm alg)
{
	ldns_key *k;

	k = ldns_key_new();
        if(!k) return LDNS_STATUS_MEM_ERR;
#ifndef S_SPLINT_S
	k->_key.key = ENGINE_load_private_key(e, key_id, UI_OpenSSL(), NULL);
        if(!k->_key.key) {
                ldns_key_free(k);
                return LDNS_STATUS_ERR;
        }
	ldns_key_set_algorithm(k, (ldns_signing_algorithm) alg);
	if (!k->_key.key) {
                ldns_key_free(k);
		return LDNS_STATUS_ENGINE_KEY_NOT_LOADED;
	} 
#endif /* splint */
	*key = k;
	return LDNS_STATUS_OK;
}