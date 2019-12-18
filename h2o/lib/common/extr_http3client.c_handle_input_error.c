#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_http3client_req_t {int /*<<< orphan*/  (* handle_input ) (struct st_h2o_http3client_req_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int,char const**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct st_h2o_http3client_req_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int,char const**) ; 

__attribute__((used)) static void handle_input_error(struct st_h2o_http3client_req_t *req, int err)
{
    const uint8_t *src = NULL, *src_end = NULL;
    const char *err_desc = NULL;
    req->handle_input(req, &src, src_end, err, &err_desc);
}