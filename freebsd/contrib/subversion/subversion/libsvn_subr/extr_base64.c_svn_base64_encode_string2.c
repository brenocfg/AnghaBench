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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  encode_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_partial_group (int /*<<< orphan*/ *,unsigned char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__ const* svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

const svn_string_t *
svn_base64_encode_string2(const svn_string_t *str,
                          svn_boolean_t break_lines,
                          apr_pool_t *pool)
{
  svn_stringbuf_t *encoded = svn_stringbuf_create_empty(pool);
  unsigned char ingroup[3];
  size_t ingrouplen = 0;
  size_t linelen = 0;

  encode_bytes(encoded, str->data, str->len, ingroup, &ingrouplen, &linelen,
               break_lines);
  encode_partial_group(encoded, ingroup, ingrouplen, linelen,
                       break_lines);
  return svn_stringbuf__morph_into_string(encoded);
}