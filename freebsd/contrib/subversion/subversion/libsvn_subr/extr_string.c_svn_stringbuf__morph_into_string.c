#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; scalar_t__ len; scalar_t__ blocksize; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_string_t ;

/* Variables and functions */

svn_string_t *
svn_stringbuf__morph_into_string(svn_stringbuf_t *strbuf)
{
  /* In debug mode, detect attempts to modify the original STRBUF object.
   */
#ifdef SVN_DEBUG
  strbuf->pool = NULL;
  strbuf->blocksize = strbuf->len + 1;
#endif

  /* Both, svn_string_t and svn_stringbuf_t are public API structures
   * since the svn epoch. Thus, we can rely on their precise layout not
   * to change.
   *
   * It just so happens that svn_string_t is structurally equivalent
   * to the (data, len) sub-set of svn_stringbuf_t. There is also no
   * difference in alignment and padding. So, we can just re-interpret
   * that part of STRBUF as a svn_string_t.
   *
   * However, since svn_string_t does not know about the blocksize
   * member in svn_stringbuf_t, any attempt to re-size the returned
   * svn_string_t might invalidate the STRBUF struct. Hence, we consider
   * the source STRBUF "consumed".
   *
   * Modifying the string character content is fine, though.
   */
  return (svn_string_t *)&strbuf->data;
}