#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct st_h2o_specific_file_handler_t {int /*<<< orphan*/  mime_type; TYPE_1__ real_path; int /*<<< orphan*/  flags; } ;
struct st_h2o_sendfile_generator_t {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  path_normalized; } ;
typedef  TYPE_2__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;

/* Variables and functions */
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 scalar_t__ ENOENT ; 
 struct st_h2o_sendfile_generator_t* create_generator (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  h2o_send_error_403 (TYPE_2__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_error_503 (TYPE_2__*,char*,char*,int /*<<< orphan*/ ) ; 
 int serve_with_generator (struct st_h2o_sendfile_generator_t*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int specific_handler_on_req(h2o_handler_t *_self, h2o_req_t *req)
{
    struct st_h2o_specific_file_handler_t *self = (void *)_self;
    struct st_h2o_sendfile_generator_t *generator;
    int is_dir;

    /* open file (or send error or return -1) */
    if ((generator = create_generator(req, self->real_path.base, self->real_path.len, &is_dir, self->flags)) == NULL) {
        if (is_dir) {
            h2o_send_error_403(req, "Access Forbidden", "access forbidden", 0);
        } else if (errno == ENOENT) {
            return -1;
        } else if (errno == ENFILE || errno == EMFILE) {
            h2o_send_error_503(req, "Service Unavailable", "please try again later", 0);
        } else {
            h2o_send_error_403(req, "Access Forbidden", "access forbidden", 0);
        }
        return 0;
    }

    return serve_with_generator(generator, req, req->path_normalized, self->real_path.base, self->real_path.len, self->mime_type);
}