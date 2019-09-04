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
struct phr_chunked_decoder {int consume_trailer; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int bufis (char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  note (char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 scalar_t__ phr_decode_chunked (struct phr_chunked_decoder*,char*,size_t*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void test_chunked_at_once(int line, int consume_trailer, const char *encoded, const char *decoded, ssize_t expected)
{
    struct phr_chunked_decoder dec = {0};
    char *buf;
    size_t bufsz;
    ssize_t ret;

    dec.consume_trailer = consume_trailer;

    note("testing at-once, source at line %d", line);

    buf = strdup(encoded);
    bufsz = strlen(buf);

    ret = phr_decode_chunked(&dec, buf, &bufsz);

    ok(ret == expected);
    ok(bufsz == strlen(decoded));
    ok(bufis(buf, bufsz, decoded));
    if (expected >= 0) {
        if (ret == expected)
            ok(bufis(buf + bufsz, ret, encoded + strlen(encoded) - ret));
        else
            ok(0);
    }

    free(buf);
}