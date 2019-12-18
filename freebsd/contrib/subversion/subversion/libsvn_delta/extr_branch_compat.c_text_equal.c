#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ svn_element__payload_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_stringbuf_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t
text_equal(svn_element__payload_t *initial_payload,
           svn_element__payload_t *final_payload)
{
  if (!initial_payload || !final_payload
      || initial_payload->kind != svn_node_file
      || final_payload->kind != svn_node_file)
    {
      return FALSE;
    }

  return svn_stringbuf_compare(initial_payload->text,
                               final_payload->text);
}