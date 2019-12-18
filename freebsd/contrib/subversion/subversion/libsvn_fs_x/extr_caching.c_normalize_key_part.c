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
struct TYPE_5__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char*,int) ; 
 TYPE_1__* svn_stringbuf_create_ensure (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
normalize_key_part(const char *original,
                   apr_pool_t *result_pool)
{
  apr_size_t i;
  apr_size_t len = strlen(original);
  svn_stringbuf_t *normalized = svn_stringbuf_create_ensure(len,
                                                            result_pool);

  for (i = 0; i < len; ++i)
    {
      char c = original[i];
      switch (c)
        {
        case ':': svn_stringbuf_appendbytes(normalized, "%_", 2);
                  break;
        case '%': svn_stringbuf_appendbytes(normalized, "%%", 2);
                  break;
        default : svn_stringbuf_appendbyte(normalized, c);
        }
    }

  return normalized->data;
}