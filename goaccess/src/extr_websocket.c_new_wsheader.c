#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int reading; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ WSHeaders ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static WSHeaders *
new_wsheader (void)
{
  WSHeaders *headers = xcalloc (1, sizeof (WSHeaders));
  memset (headers->buf, 0, sizeof (headers->buf));
  headers->reading = 1;

  return headers;
}