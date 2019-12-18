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
struct TYPE_3__ {int /*<<< orphan*/  new_data; int /*<<< orphan*/  num_ops; int /*<<< orphan*/  ops; } ;
typedef  TYPE_1__ svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;

/* Variables and functions */
 int /*<<< orphan*/  serialize_svn_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serialize_txdelta_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_temp_serializer__pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__push (int /*<<< orphan*/ *,void const* const*,int) ; 

__attribute__((used)) static void
serialize_txdeltawindow(svn_temp_serializer__context_t *context,
                        svn_txdelta_window_t * const * w)
{
  svn_txdelta_window_t *window = *w;

  /* serialize the window struct itself */
  svn_temp_serializer__push(context, (const void * const *)w, sizeof(**w));

  /* serialize its sub-structures */
  serialize_txdelta_ops(context, &window->ops, window->num_ops);
  serialize_svn_string(context, &window->new_data);

  svn_temp_serializer__pop(context);
}