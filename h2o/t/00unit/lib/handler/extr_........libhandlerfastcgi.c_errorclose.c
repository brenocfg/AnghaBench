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
struct st_fcgi_generator_t {int /*<<< orphan*/ * req; scalar_t__ sent_headers; } ;
typedef  int /*<<< orphan*/  h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  close_generator (struct st_fcgi_generator_t*) ; 
 int /*<<< orphan*/  h2o_send_error_503 (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_eos_and_close (struct st_fcgi_generator_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void errorclose(struct st_fcgi_generator_t *generator)
{
    if (generator->sent_headers) {
        send_eos_and_close(generator, 0);
    } else {
        h2o_req_t *req = generator->req;
        close_generator(generator);
        h2o_send_error_503(req, "Internal Server Error", "Internal Server Error", 0);
    }
}