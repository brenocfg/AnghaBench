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
struct lev_storage_file {int /*<<< orphan*/  md5; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  md5 (unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int md5_check (struct lev_storage_file *E, unsigned char *a) {
  unsigned char m[16];
  md5 (a, E->size, m);
  return !memcmp (m, E->md5, 16);
}