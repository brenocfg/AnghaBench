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

/* Variables and functions */
 int done_testing () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_evloop_create () ; 
 int /*<<< orphan*/  h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  init_openssl () ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_issues293 ; 
 int /*<<< orphan*/  test_lib__common__balancer__least_conn_c ; 
 int /*<<< orphan*/  test_lib__common__balancer__roundrobin_c ; 
 int /*<<< orphan*/  test_lib__common__cache_c ; 
 int /*<<< orphan*/  test_lib__common__hostinfo_c ; 
 int /*<<< orphan*/  test_lib__common__httpclient_c ; 
 int /*<<< orphan*/  test_lib__common__multithread_c ; 
 int /*<<< orphan*/  test_lib__common__serverutil_c ; 
 int /*<<< orphan*/  test_lib__common__socket_c ; 
 int /*<<< orphan*/  test_lib__common__string_c ; 
 int /*<<< orphan*/  test_lib__common__time_c ; 
 int /*<<< orphan*/  test_lib__common__timerwheel_c ; 
 int /*<<< orphan*/  test_lib__common__url_c ; 
 int /*<<< orphan*/  test_lib__core__headers_c ; 
 int /*<<< orphan*/  test_lib__core__proxy_c ; 
 int /*<<< orphan*/  test_lib__core__util_c ; 
 int /*<<< orphan*/  test_lib__handler__fastcgi_c ; 
 int /*<<< orphan*/  test_lib__handler__file_c ; 
 int /*<<< orphan*/  test_lib__handler__gzip_c ; 
 int /*<<< orphan*/  test_lib__handler__headers_c ; 
 int /*<<< orphan*/  test_lib__handler__mimemap_c ; 
 int /*<<< orphan*/  test_lib__handler__redirect_c ; 
 int /*<<< orphan*/  test_lib__http2__cache_digests ; 
 int /*<<< orphan*/  test_lib__http2__casper ; 
 int /*<<< orphan*/  test_lib__http2__hpack ; 
 int /*<<< orphan*/  test_lib__http2__scheduler ; 
 int /*<<< orphan*/  test_lib__http3_frames ; 
 int /*<<< orphan*/  test_lib__http3_qpack ; 
 int /*<<< orphan*/  test_loop ; 
 int /*<<< orphan*/  test_loopback ; 
 int /*<<< orphan*/  test_percent_encode_zero_byte ; 
 int /*<<< orphan*/  test_src__ssl_c ; 
 int /*<<< orphan*/  uv_loop_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_loop_init (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
    init_openssl();

    { /* library tests */
        subtest("lib/common/balancer/least_conn.c", test_lib__common__balancer__least_conn_c);
        subtest("lib/common/balancer/roundrobin.c", test_lib__common__balancer__roundrobin_c);
        subtest("lib/cache.c", test_lib__common__cache_c);
        subtest("lib/common/multithread.c", test_lib__common__multithread_c);
        subtest("lib/common/hostinfo.c", test_lib__common__hostinfo_c);
        subtest("lib/common/httpclient.c", test_lib__common__httpclient_c);
        subtest("lib/common/serverutil.c", test_lib__common__serverutil_c);
        subtest("lib/common/serverutil.c", test_lib__common__socket_c);
        subtest("lib/common/string.c", test_lib__common__string_c);
        subtest("lib/common/url.c", test_lib__common__url_c);
        subtest("lib/common/time.c", test_lib__common__time_c);
        subtest("lib/common/timerwheel.c", test_lib__common__timerwheel_c);
        subtest("lib/core/headers.c", test_lib__core__headers_c);
        subtest("lib/core/proxy.c", test_lib__core__proxy_c);
        subtest("lib/core/util.c", test_lib__core__util_c);
        subtest("lib/handler/headers.c", test_lib__handler__headers_c);
        subtest("lib/handler/mimemap.c", test_lib__handler__mimemap_c);
        subtest("lib/http2/hpack.c", test_lib__http2__hpack);
        subtest("lib/http2/scheduler.c", test_lib__http2__scheduler);
        subtest("lib/http2/casper.c", test_lib__http2__casper);
        subtest("lib/http2/cache_digests.c", test_lib__http2__cache_digests);
        subtest("lib/http3/frame.c", test_lib__http3_frames);
        subtest("lib/http3/qpack.c", test_lib__http3_qpack);
    }

    { /* tests that use the run loop */
#if H2O_USE_LIBUV
        test_loop = h2o_mem_alloc(sizeof(*test_loop));
        uv_loop_init(test_loop);
#else
        test_loop = h2o_evloop_create();
#endif

        subtest("lib/t/test.c/loopback", test_loopback);
        subtest("lib/fastcgi.c", test_lib__handler__fastcgi_c);
        subtest("lib/file.c", test_lib__handler__file_c);
        subtest("lib/gzip.c", test_lib__handler__gzip_c);
        subtest("lib/redirect.c", test_lib__handler__redirect_c);
        subtest("issues/293.c", test_issues293);
        subtest("issues/percent-encode-zero-byte.c", test_percent_encode_zero_byte);

#if H2O_USE_LIBUV
        uv_loop_close(test_loop);
        free(test_loop);
#else
// h2o_evloop_destroy(loop);
#endif
    }

    { /* src tests */
        subtest("src/ssl.c", test_src__ssl_c);
    }

    return done_testing();
}