#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  h2o_multithread_receiver_t ;
typedef  int /*<<< orphan*/  h2o_multithread_queue_t ;
struct TYPE_5__ {void* ratio; } ;
struct TYPE_6__ {int const member_2; int const member_3; int const member_4; int member_7; int /*<<< orphan*/  loop; int /*<<< orphan*/  getaddr_receiver; TYPE_1__ http2; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ h2o_httpclient_ctx_t ;
struct TYPE_7__ {void* len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int H2O_SOCKET_INITIAL_INPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ body_size ; 
 void* chunk_size ; 
 scalar_t__ cnt_left ; 
 void* delay_interval_ms ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  h2o_evloop_create () ; 
 int /*<<< orphan*/  h2o_evloop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_hostinfo_getaddr_receiver ; 
 int /*<<< orphan*/  h2o_mem_alloc (void*) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_multithread_create_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_multithread_register_receiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* http2_ratio ; 
 TYPE_4__ iov_filler ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,void*) ; 
 int /*<<< orphan*/  method ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  pool ; 
 int ssl_verify_none ; 
 int /*<<< orphan*/  start_request (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* url ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
    h2o_multithread_queue_t *queue;
    h2o_multithread_receiver_t getaddr_receiver;

    const uint64_t timeout = 5000; /* 5 seconds */
    h2o_httpclient_ctx_t ctx = {
        NULL, /* loop */
        &getaddr_receiver,
        timeout,                                 /* io_timeout */
        timeout,                                 /* connect_timeout */
        timeout,                                 /* first_byte_timeout */
        NULL,                                    /* websocket_timeout */
        0,                                       /* keepalive_timeout */
        H2O_SOCKET_INITIAL_INPUT_BUFFER_SIZE * 2 /* max_buffer_size */
    };
    int opt;

    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();

    while ((opt = getopt(argc, argv, "t:m:b:c:i:r:k")) != -1) {
        switch (opt) {
        case 't':
            cnt_left = atoi(optarg);
            break;
        case 'm':
            method = optarg;
            break;
        case 'b':
            body_size = atoi(optarg);
            if (body_size <= 0) {
                fprintf(stderr, "body size must be greater than 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'c':
            chunk_size = atoi(optarg);
            if (chunk_size <= 0) {
                fprintf(stderr, "chunk size must be greater than 0\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'i':
            delay_interval_ms = atoi(optarg);
            break;
        case 'r':
            http2_ratio = atoi(optarg);
            break;
        case 'k':
            ssl_verify_none = 1;
            break;
        default:
            usage(argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (argc - optind != 1) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    url = argv[optind];

    if (body_size != 0) {
        iov_filler.base = h2o_mem_alloc(chunk_size);
        memset(iov_filler.base, 'a', chunk_size);
        iov_filler.len = chunk_size;
    }
    h2o_mem_init_pool(&pool);

    ctx.http2.ratio = http2_ratio;

/* setup context */
#if H2O_USE_LIBUV
    ctx.loop = uv_loop_new();
#else
    ctx.loop = h2o_evloop_create();
#endif

    queue = h2o_multithread_create_queue(ctx.loop);
    h2o_multithread_register_receiver(queue, ctx.getaddr_receiver, h2o_hostinfo_getaddr_receiver);

    /* setup the first request */
    start_request(&ctx);

    while (cnt_left != 0) {
#if H2O_USE_LIBUV
        uv_run(ctx.loop, UV_RUN_ONCE);
#else
        h2o_evloop_run(ctx.loop, INT32_MAX);
#endif
    }

    return 0;
}