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
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ md5_t ;

/* Variables and functions */
 int /*<<< orphan*/  md5 (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const* const) ; 

__attribute__((used)) static void uri2md5 (const char *const uri, md5_t *M) {
  md5 ((unsigned char *) uri, strlen (uri), M->c);
  #ifdef CACHE_TEST_MD5_COLLISION
  memset (M->c, 0, 8);
  #endif
}