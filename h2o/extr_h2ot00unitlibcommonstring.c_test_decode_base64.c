#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_3__ {char* base; scalar_t__ len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_base64_encode (char*,int /*<<< orphan*/  const*,scalar_t__,int) ; 
 TYPE_1__ h2o_decode_base64url (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_decode_base64(void)
{
    h2o_mem_pool_t pool;
    char buf[256];

    h2o_mem_init_pool(&pool);

    h2o_iovec_t src = {H2O_STRLIT("The quick brown fox jumps over the lazy dog.")}, decoded;
    h2o_base64_encode(buf, (const uint8_t *)src.base, src.len, 1);
    ok(strcmp(buf, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZy4") == 0);
    decoded = h2o_decode_base64url(&pool, buf, strlen(buf));
    ok(src.len == decoded.len);
    ok(strcmp(decoded.base, src.base) == 0);

    h2o_mem_clear_pool(&pool);
}