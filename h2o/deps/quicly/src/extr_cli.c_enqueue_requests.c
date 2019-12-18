#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct st_stream_data_t {int /*<<< orphan*/ * outfp; } ;
struct TYPE_6__ {struct st_stream_data_t* data; } ;
typedef  TYPE_1__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_7__ {char* path; scalar_t__ to_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enqueue_requests_at ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int quicly_open_stream (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_streambuf_egress_shutdown (TYPE_1__*) ; 
 TYPE_3__* reqs ; 
 int /*<<< orphan*/  send_str (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void enqueue_requests(quicly_conn_t *conn)
{
    size_t i;
    int ret;

    for (i = 0; reqs[i].path != NULL; ++i) {
        char req[1024], destfile[1024];
        quicly_stream_t *stream;
        ret = quicly_open_stream(conn, &stream, 0);
        assert(ret == 0);
        sprintf(req, "GET %s\r\n", reqs[i].path);
        send_str(stream, req);
        quicly_streambuf_egress_shutdown(stream);

        if (reqs[i].to_file) {
            struct st_stream_data_t *stream_data = stream->data;
            sprintf(destfile, "%s.downloaded", strrchr(reqs[i].path, '/') + 1);
            stream_data->outfp = fopen(destfile, "w");
            if (stream_data->outfp == NULL) {
                fprintf(stderr, "failed to open destination file:%s:%s\n", reqs[i].path, strerror(errno));
                exit(1);
            }
        }
    }
    enqueue_requests_at = INT64_MAX;
}