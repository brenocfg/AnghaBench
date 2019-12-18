#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  prev_buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  parser; int /*<<< orphan*/  feed; int /*<<< orphan*/  feed_disconnect; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  static_request; int /*<<< orphan*/  app; int /*<<< orphan*/  matcher; int /*<<< orphan*/  error_handler; int /*<<< orphan*/  transport; int /*<<< orphan*/  writelines; int /*<<< orphan*/  write; int /*<<< orphan*/  create_task; int /*<<< orphan*/  request_logger; TYPE_1__ gather; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  Parser_dealloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Pipeline_dealloc (int /*<<< orphan*/ *) ; 
 TYPE_3__* Py_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Request_dealloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Protocol_dealloc(Protocol* self)
{
  Py_XDECREF(self->gather.prev_buffer);
  Py_XDECREF(self->request_logger);
  Py_XDECREF(self->create_task);
  Py_XDECREF(self->write);
  Py_XDECREF(self->writelines);
  Py_XDECREF(self->transport);
  Py_XDECREF(self->error_handler);
  Py_XDECREF(self->matcher);
  Py_XDECREF(self->app);
  Request_dealloc(&self->static_request);
  Pipeline_dealloc(&self->pipeline);
#ifdef PARSER_STANDALONE
  Py_XDECREF(self->feed_disconnect);
  Py_XDECREF(self->feed);
#else
  Parser_dealloc(&self->parser);
#endif

  Py_TYPE(self)->tp_free((PyObject*)self);
}