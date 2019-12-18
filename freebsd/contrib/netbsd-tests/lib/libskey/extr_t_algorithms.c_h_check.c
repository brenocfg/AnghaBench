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
 int /*<<< orphan*/  H_REQUIRE (char*,char const*) ; 
 int /*<<< orphan*/  btoa8 (char*,char*) ; 
 int /*<<< orphan*/  f (char*) ; 
 int /*<<< orphan*/  keycrunch (char*,char const*,char const*) ; 
 int /*<<< orphan*/  skey_set_algorithm (char const*) ; 

__attribute__((used)) static void
h_check(const char *pass, const char *seed,
        const char *algo, const char *zero,
        const char *one,  const char *nine)
{
	char prn[64];
	char data[16];
	int i;

	skey_set_algorithm(algo);

	keycrunch(data, seed, pass);
	btoa8(prn, data);
	H_REQUIRE(prn, zero);

	f(data);
	btoa8(prn, data);
	H_REQUIRE(prn, one);

	for(i = 1; i < 99; ++i)
		f(data);
	btoa8(prn, data);
	H_REQUIRE(prn, nine);
}