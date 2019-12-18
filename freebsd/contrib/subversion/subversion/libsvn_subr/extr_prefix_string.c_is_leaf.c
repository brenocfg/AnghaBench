#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_4__ {scalar_t__* data; } ;
struct TYPE_5__ {TYPE_1__ key; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */

__attribute__((used)) static svn_boolean_t
is_leaf(node_t *node)
{
  /* If this NOT a leaf node and this node has ...
   *    ... 8 chars, data[7] will not be NUL because we only support
   *        NUL-*terminated* strings.
   *    ... less than 8 chars, this will be set to 0xff
   *        (any other non-NUL would do as well but this is not valid UTF8
   *         making it easy to recognize during debugging etc.) */
  return node->key.data[7] == 0;
}