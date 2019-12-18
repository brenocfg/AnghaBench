#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct query_state {TYPE_3__* config_entry; } ;
struct cache_entry_params {int dummy; } ;
typedef  int /*<<< orphan*/  cache_entry ;
struct TYPE_6__ {char* entry_name; } ;
struct TYPE_7__ {TYPE_1__ cep; } ;
struct TYPE_8__ {TYPE_2__ mp_cache_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  INVALID_CACHE_ENTRY ; 
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/  (*) (struct query_state*,char const*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/  (*) (struct query_state*,char const*)) ; 
 int /*<<< orphan*/  configuration_entry_add_mp_cache_entry (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_entry (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_rdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_wrlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_cache_entry (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  register_cache_entry (int /*<<< orphan*/ ,struct cache_entry_params*) ; 
 int /*<<< orphan*/  s_cache ; 
 int /*<<< orphan*/  s_configuration ; 

cache_entry register_new_mp_cache_entry(struct query_state *qstate,
	const char *dec_cache_entry_name)
{
	cache_entry c_entry;
	char *en_bkp;

	TRACE_IN(register_new_mp_cache_entry);
	c_entry = INVALID_CACHE_ENTRY;
	configuration_lock_entry(qstate->config_entry, CELT_MULTIPART);

	configuration_lock_wrlock(s_configuration);
	en_bkp = qstate->config_entry->mp_cache_params.cep.entry_name;
	qstate->config_entry->mp_cache_params.cep.entry_name =
		(char *)dec_cache_entry_name;
	register_cache_entry(s_cache, (struct cache_entry_params *)
		&qstate->config_entry->mp_cache_params);
	qstate->config_entry->mp_cache_params.cep.entry_name = en_bkp;
	configuration_unlock(s_configuration);

	configuration_lock_rdlock(s_configuration);
	c_entry = find_cache_entry(s_cache,
		dec_cache_entry_name);
	configuration_unlock(s_configuration);

	configuration_entry_add_mp_cache_entry(qstate->config_entry,
		c_entry);

	configuration_unlock_entry(qstate->config_entry,
		CELT_MULTIPART);

	TRACE_OUT(register_new_mp_cache_entry);
	return (c_entry);
}