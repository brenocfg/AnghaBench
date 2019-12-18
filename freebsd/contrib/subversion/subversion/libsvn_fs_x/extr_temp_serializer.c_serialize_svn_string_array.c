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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  serialize_svn_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  svn_temp_serializer__pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__push (int /*<<< orphan*/ *,void const* const*,int) ; 

__attribute__((used)) static void
serialize_svn_string_array(svn_temp_serializer__context_t *context,
                           const svn_string_t ***strings,
                           apr_size_t count)
{
  apr_size_t i;
  const svn_string_t **entries = *strings;

  /* serialize COUNT entries pointers (the array) */
  svn_temp_serializer__push(context,
                            (const void * const *)strings,
                            count * sizeof(const char*));

  /* serialize array elements */
  for (i = 0; i < count; ++i)
    serialize_svn_string(context, &entries[i]);

  svn_temp_serializer__pop(context);
}