#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int size; TYPE_5__* entries; } ;
struct TYPE_14__ {int size; TYPE_2__* entries; } ;
struct TYPE_18__ {int complete; TYPE_6__ url_only; TYPE_3__ url_and_etag; } ;
struct TYPE_19__ {TYPE_7__ fresh; } ;
typedef  TYPE_8__ h2o_cache_digests_t ;
struct TYPE_15__ {int size; int* entries; } ;
struct TYPE_16__ {int capacity_bits; TYPE_4__ keys; } ;
struct TYPE_12__ {scalar_t__ size; } ;
struct TYPE_13__ {int capacity_bits; TYPE_1__ keys; } ;

/* Variables and functions */
 scalar_t__ H2O_CACHE_DIGESTS_STATE_FRESH ; 
 scalar_t__ H2O_CACHE_DIGESTS_STATE_NOT_CACHED ; 
 scalar_t__ H2O_CACHE_DIGESTS_STATE_UNKNOWN ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_cache_digests_destroy (TYPE_8__*) ; 
 int /*<<< orphan*/  h2o_cache_digests_load_header (TYPE_8__**,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_cache_digests_lookup_by_url (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_decode(void)
{
    h2o_cache_digests_t *digests = NULL;

    h2o_cache_digests_load_header(&digests, H2O_STRLIT("AeLA"));
    ok(digests != NULL);
    if (digests == NULL)
        return;
    ok(digests->fresh.url_only.size == 1);
    ok(digests->fresh.url_and_etag.size == 0);
    ok(digests->fresh.url_only.entries[0].capacity_bits == 7);
    ok(digests->fresh.url_only.entries[0].keys.size == 1);
    ok(digests->fresh.url_only.entries[0].keys.entries[0] == 0x0b);
    ok(!digests->fresh.complete);

    ok(h2o_cache_digests_lookup_by_url(digests, H2O_STRLIT("https://127.0.0.1.xip.io:8081/cache-digests.cgi/hello.js")) ==
       H2O_CACHE_DIGESTS_STATE_FRESH);
    ok(h2o_cache_digests_lookup_by_url(digests, H2O_STRLIT("https://127.0.0.1.xip.io:8081/notfound.js")) ==
       H2O_CACHE_DIGESTS_STATE_UNKNOWN);

    h2o_cache_digests_load_header(&digests, H2O_STRLIT("FOO; stale, AcA; validators; complete"));
    ok(digests->fresh.url_only.size == 1);
    ok(digests->fresh.url_and_etag.size == 1);
    ok(digests->fresh.url_and_etag.entries[0].capacity_bits == 7);
    ok(digests->fresh.url_and_etag.entries[0].keys.size == 0);
    ok(digests->fresh.complete);

    ok(h2o_cache_digests_lookup_by_url(digests, H2O_STRLIT("https://127.0.0.1.xip.io:8081/notfound.js")) ==
       H2O_CACHE_DIGESTS_STATE_NOT_CACHED);
    ok(h2o_cache_digests_lookup_by_url(digests, H2O_STRLIT("https://127.0.0.1.xip.io:8081/cache-digests.cgi/hello.js")) ==
       H2O_CACHE_DIGESTS_STATE_FRESH);

    h2o_cache_digests_load_header(&digests, H2O_STRLIT("AcA; reset"));
    ok(digests->fresh.url_only.size == 1);
    ok(digests->fresh.url_and_etag.size == 0);
    ok(digests->fresh.url_only.entries[0].capacity_bits == 7);
    ok(digests->fresh.url_only.entries[0].keys.size == 0);
    ok(!digests->fresh.complete);

    h2o_cache_digests_destroy(digests);
}