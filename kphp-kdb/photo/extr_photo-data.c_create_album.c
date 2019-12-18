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
typedef  int /*<<< orphan*/  user ;
struct lev_photo_create_album {int dummy; } ;

/* Variables and functions */
 int user_create_album (int /*<<< orphan*/ *) ; 

int create_album (user *u, struct lev_photo_create_album *E, int size) {
  return user_create_album (u);
}