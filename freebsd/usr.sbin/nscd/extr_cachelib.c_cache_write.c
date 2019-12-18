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
struct timeval {int dummy; } ;
struct cache_policy_item_ {char const* key; size_t key_size; char const creation_time; struct cache_policy_item_* connected_item; } ;
struct cache_policy_ {int /*<<< orphan*/  (* add_item_func ) (struct cache_policy_*,struct cache_policy_item_*) ;struct cache_policy_item_* (* create_item_func ) () ;} ;
struct cache_ht_item_data_ {char* key; size_t key_size; int confidence; size_t value_size; char const* value; struct cache_policy_item_* fifo_policy_item; } ;
struct cache_ht_item_ {int dummy; } ;
struct cache_entry_ {TYPE_1__* params; } ;
struct TYPE_4__ {int confidence_threshold; scalar_t__ max_elemsize; } ;
struct cache_common_entry_ {int policies_size; scalar_t__ items_size; struct cache_policy_** policies; TYPE_2__ common_params; int /*<<< orphan*/  (* get_time_func ) (char const*) ;int /*<<< orphan*/  items; } ;
typedef  scalar_t__ hashtable_index_t ;
struct TYPE_3__ {scalar_t__ entry_type; } ;

/* Variables and functions */
 scalar_t__ CET_COMMON ; 
 scalar_t__ HASHTABLE_CALCULATE_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cache_ht_item_data_*) ; 
 scalar_t__ HASHTABLE_ENTRIES_COUNT (int /*<<< orphan*/ *) ; 
 struct cache_ht_item_data_* HASHTABLE_ENTRY_FIND (int /*<<< orphan*/ ,struct cache_ht_item_*,struct cache_ht_item_data_*) ; 
 int /*<<< orphan*/  HASHTABLE_ENTRY_STORE (int /*<<< orphan*/ ,struct cache_ht_item_*,struct cache_ht_item_data_*) ; 
 struct cache_ht_item_* HASHTABLE_GET_ENTRY (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct cache_entry_*,char const*,size_t,char const*,size_t)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct cache_entry_*,char const*,size_t,char const*,size_t)) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_elemsize_common_continue_func ; 
 int /*<<< orphan*/  cache_ht_ ; 
 int /*<<< orphan*/  flush_cache_policy (struct cache_common_entry_*,struct cache_policy_*,struct cache_policy_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const*) ; 
 void* malloc (size_t) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct cache_ht_item_data_*,int /*<<< orphan*/ ,int) ; 
 struct cache_policy_item_* stub1 () ; 
 int /*<<< orphan*/  stub2 (char const*) ; 
 struct cache_policy_item_* stub3 () ; 
 int /*<<< orphan*/  stub4 (struct cache_policy_*,struct cache_policy_item_*) ; 
 int /*<<< orphan*/  stub5 (struct cache_policy_*,struct cache_policy_item_*) ; 

int
cache_write(struct cache_entry_ *entry, const char *key, size_t key_size,
    	char const *value, size_t value_size)
{
	struct cache_common_entry_	*common_entry;
	struct cache_ht_item_data_	item_data, *find_res;
	struct cache_ht_item_		*item;
	hashtable_index_t	hash;

	struct cache_policy_		*policy, *connected_policy;
	struct cache_policy_item_	*policy_item;
	struct cache_policy_item_	*connected_policy_item;

	TRACE_IN(cache_write);
	assert(entry != NULL);
	assert(key != NULL);
	assert(value != NULL);
	assert(entry->params->entry_type == CET_COMMON);

	common_entry = (struct cache_common_entry_ *)entry;

	memset(&item_data, 0, sizeof(struct cache_ht_item_data_));
	/* can't avoid the cast here */
	item_data.key = (char *)key;
	item_data.key_size = key_size;

	hash = HASHTABLE_CALCULATE_HASH(cache_ht_, &common_entry->items,
		&item_data);
	assert(hash < HASHTABLE_ENTRIES_COUNT(&common_entry->items));

	item = HASHTABLE_GET_ENTRY(&(common_entry->items), hash);
	find_res = HASHTABLE_ENTRY_FIND(cache_ht_, item, &item_data);
	if (find_res != NULL) {
		if (find_res->confidence < common_entry->common_params.confidence_threshold) {
		  	/* duplicate entry is no error, if confidence is low */
			if ((find_res->value_size == value_size) &&
			    (memcmp(find_res->value, value, value_size) == 0)) {
				/* increase confidence on exact match (key and values) */
				find_res->confidence++;
			} else {
				/* create new entry with low confidence, if value changed */
				free(item_data.value);
				item_data.value = malloc(value_size);
				assert(item_data.value != NULL);
				memcpy(item_data.value, value, value_size);
				item_data.value_size = value_size;
				find_res->confidence = 1;
			}
			TRACE_OUT(cache_write);
			return (0);
		}
		TRACE_OUT(cache_write);
		return (-1);
	}

	item_data.key = malloc(key_size);
	memcpy(item_data.key, key, key_size);

	item_data.value = malloc(value_size);
	assert(item_data.value != NULL);

	memcpy(item_data.value, value, value_size);
	item_data.value_size = value_size;

	item_data.confidence = 1;

	policy_item = common_entry->policies[0]->create_item_func();
	policy_item->key = item_data.key;
	policy_item->key_size = item_data.key_size;
	common_entry->get_time_func(&policy_item->creation_time);

	if (common_entry->policies_size > 1) {
		connected_policy_item =
			common_entry->policies[1]->create_item_func();
		memcpy(&connected_policy_item->creation_time,
			&policy_item->creation_time,
			sizeof(struct timeval));
		connected_policy_item->key = policy_item->key;
		connected_policy_item->key_size = policy_item->key_size;

		connected_policy_item->connected_item = policy_item;
		policy_item->connected_item = connected_policy_item;
	}

	item_data.fifo_policy_item = policy_item;

	common_entry->policies[0]->add_item_func(common_entry->policies[0],
		policy_item);
	if (common_entry->policies_size > 1)
		common_entry->policies[1]->add_item_func(
			common_entry->policies[1], connected_policy_item);

	HASHTABLE_ENTRY_STORE(cache_ht_, item, &item_data);
	++common_entry->items_size;

	if ((common_entry->common_params.max_elemsize != 0) &&
		(common_entry->items_size >
		common_entry->common_params.max_elemsize)) {
		if (common_entry->policies_size > 1) {
			policy = common_entry->policies[1];
			connected_policy = common_entry->policies[0];
		} else {
			policy = common_entry->policies[0];
			connected_policy = NULL;
		}

		flush_cache_policy(common_entry, policy, connected_policy,
			cache_elemsize_common_continue_func);
	}

	TRACE_OUT(cache_write);
	return (0);
}