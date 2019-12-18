#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  RequestType; } ;
struct TYPE_7__ {int /*<<< orphan*/ * prev_buffer; } ;
struct TYPE_9__ {TYPE_1__ gather; int /*<<< orphan*/ * request_logger; int /*<<< orphan*/ * create_task; int /*<<< orphan*/ * write; int /*<<< orphan*/ * transport; int /*<<< orphan*/ * error_handler; int /*<<< orphan*/ * matcher; int /*<<< orphan*/ * app; int /*<<< orphan*/  static_request; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  parser; int /*<<< orphan*/ * feed_disconnect; int /*<<< orphan*/ * feed; } ;
struct TYPE_8__ {scalar_t__ (* tp_alloc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  Parser_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Pipeline_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* request_capi ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
Protocol_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  Protocol* self = NULL;

  self = (Protocol*)type->tp_alloc(type, 0);
  if(!self)
    goto finally;

#ifdef PARSER_STANDALONE
  self->feed = NULL;
  self->feed_disconnect = NULL;
#else
  Parser_new(&self->parser);
#endif
  Pipeline_new(&self->pipeline);
  Request_new(request_capi->RequestType, &self->static_request);
  self->app = NULL;
  self->matcher = NULL;
  self->error_handler = NULL;
  self->transport = NULL;
  self->write = NULL;
  self->create_task = NULL;
  self->request_logger = NULL;

  self->gather.prev_buffer = NULL;

  finally:
  return (PyObject*)self;
}