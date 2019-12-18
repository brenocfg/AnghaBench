#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_5__ {size_t len; void* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int count; char** keys; int /*<<< orphan*/ * values; } ;
typedef  TYPE_2__ properties_data_t ;
typedef  int /*<<< orphan*/  properties ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serialize_cstring_array (int /*<<< orphan*/ *,char***,int) ; 
 int /*<<< orphan*/  serialize_svn_string_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 TYPE_1__* svn_temp_serializer__get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_temp_serializer__init (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__serialize_properties(void **data,
                                apr_size_t *data_len,
                                void *in,
                                apr_pool_t *pool)
{
  apr_hash_t *hash = in;
  properties_data_t properties;
  svn_temp_serializer__context_t *context;
  apr_hash_index_t *hi;
  svn_stringbuf_t *serialized;
  apr_size_t i;

  /* create our auxiliary data structure */
  properties.count = apr_hash_count(hash);
  properties.keys = apr_palloc(pool, sizeof(const char*) * (properties.count + 1));
  properties.values = apr_palloc(pool, sizeof(const svn_string_t *) * properties.count);

  /* populate it with the hash entries */
  for (hi = apr_hash_first(pool, hash), i=0; hi; hi = apr_hash_next(hi), ++i)
    {
      properties.keys[i] = apr_hash_this_key(hi);
      properties.values[i] = apr_hash_this_val(hi);
    }

  /* serialize it */
  context = svn_temp_serializer__init(&properties,
                                      sizeof(properties),
                                      properties.count * 100,
                                      pool);

  properties.keys[i] = "";
  serialize_cstring_array(context, &properties.keys, properties.count + 1);
  serialize_svn_string_array(context, &properties.values, properties.count);

  /* return the serialized result */
  serialized = svn_temp_serializer__get(context);

  *data = serialized->data;
  *data_len = serialized->len;

  return SVN_NO_ERROR;
}