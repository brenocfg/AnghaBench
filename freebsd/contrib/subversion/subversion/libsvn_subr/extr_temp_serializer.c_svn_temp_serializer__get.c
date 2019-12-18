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
struct TYPE_3__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ svn_temp_serializer__context_t ;
typedef  int /*<<< orphan*/  svn_stringbuf_t ;

/* Variables and functions */

svn_stringbuf_t *
svn_temp_serializer__get(svn_temp_serializer__context_t *context)
{
  return context->buffer;
}