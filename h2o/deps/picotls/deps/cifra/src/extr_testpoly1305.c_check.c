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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cf_poly1305 ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_poly1305_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_poly1305_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t unhex (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void check(const char *rstr, const char *sstr,
                  const char *msgstr, const char *tagstr)
{
  uint8_t r[16], s[16], tag[16];
  uint8_t msg[132], out[16];

  unhex(r, sizeof r, rstr);
  unhex(s, sizeof s, sstr);
  size_t nmsg = unhex(msg, sizeof msg, msgstr);
  unhex(tag, sizeof tag, tagstr);

  cf_poly1305 ctx;
  cf_poly1305_init(&ctx, r, s);
  cf_poly1305_update(&ctx, msg, nmsg);
  cf_poly1305_finish(&ctx, out);

  TEST_CHECK(memcmp(out, tag, 16) == 0);
}