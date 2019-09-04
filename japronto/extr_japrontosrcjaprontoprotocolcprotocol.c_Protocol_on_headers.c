#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* Request_from_raw ) (int /*<<< orphan*/ *,char*,size_t,char*,size_t,int,void*,size_t) ;int /*<<< orphan*/  RequestType; } ;
struct TYPE_5__ {int /*<<< orphan*/  static_request; } ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  Request_dealloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* request_capi ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,size_t,char*,size_t,int,void*,size_t) ; 

Protocol*
Protocol_on_headers(Protocol* self, char* method, size_t method_len,
                    char* path, size_t path_len, int minor_version,
                    void* headers, size_t num_headers)
{
  Protocol* result = self;

  Request_dealloc(&self->static_request);
  Request_new(request_capi->RequestType, &self->static_request);

  request_capi->Request_from_raw(
    &self->static_request, method, method_len, path, path_len, minor_version,
    headers, num_headers);

  goto finally;

  finally:
  return result;
}