#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry_type; } ;
struct timeval {int max_elemsize; int satisf_elemsize; TYPE_2__ max_lifetime; int /*<<< orphan*/  max_sessions; TYPE_1__ cep; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  policy; int /*<<< orphan*/  confidence_threshold; int /*<<< orphan*/  cache_entries_size; } ;
struct mp_cache_entry_params {int max_elemsize; int satisf_elemsize; TYPE_2__ max_lifetime; int /*<<< orphan*/  max_sessions; TYPE_1__ cep; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  policy; int /*<<< orphan*/  confidence_threshold; int /*<<< orphan*/  cache_entries_size; } ;
struct configuration_entry {int dummy; } ;
struct common_cache_entry_params {int max_elemsize; int satisf_elemsize; TYPE_2__ max_lifetime; int /*<<< orphan*/  max_sessions; TYPE_1__ cep; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  policy; int /*<<< orphan*/  confidence_threshold; int /*<<< orphan*/  cache_entries_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CET_COMMON ; 
 int /*<<< orphan*/  CET_MULTIPART ; 
 int /*<<< orphan*/  CPT_FIFO ; 
 int /*<<< orphan*/  CPT_LRU ; 
 int /*<<< orphan*/  DEFAULT_CACHE_HT_SIZE ; 
 int /*<<< orphan*/  DEFAULT_COMMON_ENTRY_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_MP_ENTRY_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_MULITPART_LIFETIME ; 
 int /*<<< orphan*/  DEFAULT_MULITPART_SESSIONS_SIZE ; 
 int DEFAULT_MULTIPART_ELEMENTS_SIZE ; 
 int /*<<< orphan*/  DEFAULT_NEGATIVE_CONF_THRESH ; 
 int DEFAULT_NEGATIVE_ELEMENTS_SIZE ; 
 int /*<<< orphan*/  DEFAULT_NEGATIVE_LIFETIME ; 
 int /*<<< orphan*/  DEFAULT_POSITIVE_CONF_THRESH ; 
 int DEFAULT_POSITIVE_ELEMENTS_SIZE ; 
 int /*<<< orphan*/  DEFAULT_POSITIVE_LIFETIME ; 
 int /*<<< orphan*/  TRACE_IN (struct configuration_entry* (*) (char const*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct configuration_entry* (*) (char const*)) ; 
 struct configuration_entry* create_configuration_entry (char const*,struct timeval*,struct timeval*,struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  memcpy (struct timeval*,struct timeval*,int) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 

struct configuration_entry *
create_def_configuration_entry(const char *name)
{
	struct common_cache_entry_params positive_params, negative_params;
	struct mp_cache_entry_params mp_params;
	struct timeval default_common_timeout, default_mp_timeout;

	struct configuration_entry *res = NULL;

	TRACE_IN(create_def_configuration_entry);
	memset(&positive_params, 0,
		sizeof(struct common_cache_entry_params));
	positive_params.cep.entry_type = CET_COMMON;
	positive_params.cache_entries_size = DEFAULT_CACHE_HT_SIZE;
	positive_params.max_elemsize = DEFAULT_POSITIVE_ELEMENTS_SIZE;
	positive_params.satisf_elemsize = DEFAULT_POSITIVE_ELEMENTS_SIZE / 2;
	positive_params.max_lifetime.tv_sec = DEFAULT_POSITIVE_LIFETIME;
	positive_params.confidence_threshold = DEFAULT_POSITIVE_CONF_THRESH;
	positive_params.policy = CPT_LRU;

	memcpy(&negative_params, &positive_params,
		sizeof(struct common_cache_entry_params));
	negative_params.max_elemsize = DEFAULT_NEGATIVE_ELEMENTS_SIZE;
	negative_params.satisf_elemsize = DEFAULT_NEGATIVE_ELEMENTS_SIZE / 2;
	negative_params.max_lifetime.tv_sec = DEFAULT_NEGATIVE_LIFETIME;
	negative_params.confidence_threshold = DEFAULT_NEGATIVE_CONF_THRESH;
	negative_params.policy = CPT_FIFO;

	memset(&default_common_timeout, 0, sizeof(struct timeval));
	default_common_timeout.tv_sec = DEFAULT_COMMON_ENTRY_TIMEOUT;

	memset(&default_mp_timeout, 0, sizeof(struct timeval));
	default_mp_timeout.tv_sec = DEFAULT_MP_ENTRY_TIMEOUT;

	memset(&mp_params, 0,
		sizeof(struct mp_cache_entry_params));
	mp_params.cep.entry_type = CET_MULTIPART;
	mp_params.max_elemsize = DEFAULT_MULTIPART_ELEMENTS_SIZE;
	mp_params.max_sessions = DEFAULT_MULITPART_SESSIONS_SIZE;
	mp_params.max_lifetime.tv_sec = DEFAULT_MULITPART_LIFETIME;

	res = create_configuration_entry(name, &default_common_timeout,
		&default_mp_timeout, &positive_params, &negative_params,
		&mp_params);

	TRACE_OUT(create_def_configuration_entry);
	return (res);
}