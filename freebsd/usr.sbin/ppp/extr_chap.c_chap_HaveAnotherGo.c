#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* local; } ;
struct chap {int peertries; int /*<<< orphan*/  auth; TYPE_1__ challenge; } ;

/* Variables and functions */
 int /*<<< orphan*/  chap_Challenge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
chap_HaveAnotherGo(struct chap *chap)
{
  if (++chap->peertries < 3) {
    /* Give the peer another shot */
    *chap->challenge.local = '\0';
    chap_Challenge(&chap->auth);
    return 1;
  }

  return 0;
}