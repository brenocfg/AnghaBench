#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  prefix_pool; } ;
typedef  TYPE_3__ svn_membuffer_t ;
struct TYPE_11__ {char* fingerprint; int key_len; scalar_t__ prefix_idx; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_12__ {TYPE_1__ entry_key; TYPE_7__ full_key; } ;
struct TYPE_14__ {int key_len; TYPE_2__ combined_key; TYPE_1__ prefix; int /*<<< orphan*/  mutex; int /*<<< orphan*/  priority; scalar_t__ deserializer; scalar_t__ serializer; TYPE_3__* membuffer; } ;
typedef  TYPE_4__ svn_membuffer_cache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {char const* digest; } ;
typedef  TYPE_5__ svn_checksum_t ;
struct TYPE_16__ {int pretend_empty; scalar_t__ error_baton; scalar_t__ error_handler; TYPE_4__* cache_internal; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_6__ svn_cache__t ;
typedef  scalar_t__ svn_cache__serialize_func_t ;
typedef  scalar_t__ svn_cache__deserialize_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int apr_ssize_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int ALIGN_VALUE (int) ; 
 int APR_HASH_KEY_STRING ; 
 scalar_t__ NO_INDEX ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int SVN_MAX_OBJECT_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ deserialize_svn_stringbuf ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  membuffer_cache_synced_vtable ; 
 int /*<<< orphan*/  membuffer_cache_vtable ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefix_pool_get (scalar_t__*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ serialize_svn_stringbuf ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_checksum (TYPE_5__**,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_membuf__create (TYPE_7__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cache__create_membuffer_cache(svn_cache__t **cache_p,
                                  svn_membuffer_t *membuffer,
                                  svn_cache__serialize_func_t serializer,
                                  svn_cache__deserialize_func_t deserializer,
                                  apr_ssize_t klen,
                                  const char *prefix,
                                  apr_uint32_t priority,
                                  svn_boolean_t thread_safe,
                                  svn_boolean_t short_lived,
                                  apr_pool_t *result_pool,
                                  apr_pool_t *scratch_pool)
{
  svn_checksum_t *checksum;
  apr_size_t prefix_len, prefix_orig_len;

  /* allocate the cache header structures
   */
  svn_cache__t *wrapper = apr_pcalloc(result_pool, sizeof(*wrapper));
  svn_membuffer_cache_t *cache = apr_pcalloc(result_pool, sizeof(*cache));

  /* initialize our internal cache header
   */
  cache->membuffer = membuffer;
  cache->serializer = serializer
                    ? serializer
                    : serialize_svn_stringbuf;
  cache->deserializer = deserializer
                      ? deserializer
                      : deserialize_svn_stringbuf;
  cache->priority = priority;
  cache->key_len = klen;

  SVN_ERR(svn_mutex__init(&cache->mutex, thread_safe, result_pool));

  /* Copy the prefix into the prefix full key. Align it to ITEM_ALIGMENT.
   * Don't forget to include the terminating NUL. */
  prefix_orig_len = strlen(prefix) + 1;
  prefix_len = ALIGN_VALUE(prefix_orig_len);

  /* Paranoia check to ensure pointer arithmetics work as expected. */
  if (prefix_orig_len >= SVN_MAX_OBJECT_SIZE)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                            _("Prefix too long"));

  /* Construct the folded prefix key. */
  SVN_ERR(svn_checksum(&checksum,
                       svn_checksum_md5,
                       prefix,
                       strlen(prefix),
                       scratch_pool));
  memcpy(cache->prefix.fingerprint, checksum->digest,
         sizeof(cache->prefix.fingerprint));
  cache->prefix.key_len = prefix_len;

  /* Fix-length keys of up to 16 bytes may be handled without storing the
   * full key separately for each item. */
  if (   (klen != APR_HASH_KEY_STRING)
      && (klen <= sizeof(cache->combined_key.entry_key.fingerprint))
      && !short_lived)
    SVN_ERR(prefix_pool_get(&cache->prefix.prefix_idx,
                            membuffer->prefix_pool,
                            prefix));
  else
    cache->prefix.prefix_idx = NO_INDEX;

  /* If key combining is not guaranteed to produce unique results, we have
   * to handle full keys.  Otherwise, leave it NULL. */
  if (cache->prefix.prefix_idx == NO_INDEX)
    {
      /* Initialize the combined key. Pre-allocate some extra room in the
       * full key such that we probably don't need to re-alloc. */
      cache->combined_key.entry_key = cache->prefix;
      svn_membuf__create(&cache->combined_key.full_key, prefix_len + 200,
                         result_pool);
      memcpy((char *)cache->combined_key.full_key.data, prefix,
             prefix_orig_len);
      memset((char *)cache->combined_key.full_key.data + prefix_orig_len, 0,
             prefix_len - prefix_orig_len);
    }
  else
    {
      /* Initialize the combined key.  We will never have the full combined
       * key, so leave it NULL and set its length to 0 to prevent access to
       * it.  Keep the fingerprint 0 as well b/c it will always be set anew
       * by combine_key(). */
      cache->combined_key.entry_key.prefix_idx = cache->prefix.prefix_idx;
      cache->combined_key.entry_key.key_len = 0;
    }

  /* initialize the generic cache wrapper
   */
  wrapper->vtable = thread_safe ? &membuffer_cache_synced_vtable
                                : &membuffer_cache_vtable;
  wrapper->cache_internal = cache;
  wrapper->error_handler = 0;
  wrapper->error_baton = 0;
  wrapper->pretend_empty = !!getenv("SVN_X_DOES_NOT_MARK_THE_SPOT");

  *cache_p = wrapper;
  return SVN_NO_ERROR;
}