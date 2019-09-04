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
 int /*<<< orphan*/  check_pkbdf2_sha256 (char*,int,char*,int,int,char*,int) ; 

__attribute__((used)) static void test_pbkdf2_sha256(void)
{
  check_pkbdf2_sha256("password", 8,
                      "salt", 4,
                      1,
                      "\x12\x0f\xb6\xcf\xfc\xf8\xb3\x2c\x43\xe7\x22\x52\x56\xc4\xf8\x37\xa8\x65\x48\xc9\x2c\xcc\x35\x48\x08\x05\x98\x7c\xb7\x0b\xe1\x7b", 32);

  check_pkbdf2_sha256("password", 8,
                      "salt", 4,
                      2,
                      "\xae\x4d\x0c\x95\xaf\x6b\x46\xd3\x2d\x0a\xdf\xf9\x28\xf0\x6d\xd0\x2a\x30\x3f\x8e\xf3\xc2\x51\xdf\xd6\xe2\xd8\x5a\x95\x47\x4c\x43", 32);

  check_pkbdf2_sha256("password", 8,
                      "salt", 4,
                      4096,
                      "\xc5\xe4\x78\xd5\x92\x88\xc8\x41\xaa\x53\x0d\xb6\x84\x5c\x4c\x8d\x96\x28\x93\xa0\x01\xce\x4e\x11\xa4\x96\x38\x73\xaa\x98\x13\x4a", 32);

  check_pkbdf2_sha256("passwordPASSWORDpassword", 24,
                      "saltSALTsaltSALTsaltSALTsaltSALTsalt", 36,
                      4096,
                      "\x34\x8c\x89\xdb\xcb\xd3\x2b\x2f\x32\xd8\x14\xb8\x11\x6e\x84\xcf\x2b\x17\x34\x7e\xbc\x18\x00\x18\x1c\x4e\x2a\x1f\xb8\xdd\x53\xe1\xc6\x35\x51\x8c\x7d\xac\x47\xe9", 40);

  check_pkbdf2_sha256("", 0,
                      "salt", 4,
                      1024,
                      "\x9e\x83\xf2\x79\xc0\x40\xf2\xa1\x1a\xa4\xa0\x2b\x24\xc4\x18\xf2\xd3\xcb\x39\x56\x0c\x96\x27\xfa\x4f\x47\xe3\xbc\xc2\x89\x7c\x3d", 32);

  check_pkbdf2_sha256("password", 8,
                      "", 0,
                      1024,
                      "\xea\x58\x08\x41\x1e\xb0\xc7\xe8\x30\xde\xab\x55\x09\x6c\xee\x58\x27\x61\xe2\x2a\x9b\xc0\x34\xe3\xec\xe9\x25\x22\x5b\x07\xbf\x46", 32);

  check_pkbdf2_sha256("\x70\x61\x73\x73\x00\x77\x6f\x72\x64", 9,
                      "\x73\x61\x00\x6c\x74", 5,
                      4096,
                      "\x89\xb6\x9d\x05\x16\xf8\x29\x89\x3c\x69\x62\x26\x65\x0a\x86\x87", 16);
}