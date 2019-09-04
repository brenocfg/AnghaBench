#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sending; } ;
struct st_fcgi_generator_t {TYPE_1__ resp; } ;
typedef  int /*<<< orphan*/  h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_generator_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_send (struct st_fcgi_generator_t*) ; 
 int /*<<< orphan*/  h2o_doublebuffer_consume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_proceed(h2o_generator_t *_generator, h2o_req_t *req)
{
    struct st_fcgi_generator_t *generator = (void *)_generator;

    h2o_doublebuffer_consume(&generator->resp.sending);
    do_send(generator);
}