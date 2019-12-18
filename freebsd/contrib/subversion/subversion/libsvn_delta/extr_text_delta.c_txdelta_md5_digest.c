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
struct txdelta_baton {TYPE_1__* checksum; int /*<<< orphan*/ * context; scalar_t__ more; } ;
struct TYPE_2__ {unsigned char const* digest; } ;

/* Variables and functions */

__attribute__((used)) static const unsigned char *
txdelta_md5_digest(void *baton)
{
  struct txdelta_baton *b = baton;
  /* If there are more windows for this stream, the digest has not yet
     been calculated.  */
  if (b->more)
    return NULL;

  /* If checksumming has not been activated, there will be no digest. */
  if (b->context == NULL)
    return NULL;

  /* The checksum should be there. */
  return b->checksum->digest;
}