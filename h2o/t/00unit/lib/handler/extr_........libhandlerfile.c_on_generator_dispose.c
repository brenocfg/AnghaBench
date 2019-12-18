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
struct st_h2o_sendfile_generator_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_file (struct st_h2o_sendfile_generator_t*) ; 

__attribute__((used)) static void on_generator_dispose(void *_self)
{
    struct st_h2o_sendfile_generator_t *self = _self;
    close_file(self);
}