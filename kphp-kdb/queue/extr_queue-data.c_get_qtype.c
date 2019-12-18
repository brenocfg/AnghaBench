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
typedef  int /*<<< orphan*/  qtype ;

/* Variables and functions */
 int /*<<< orphan*/  Q_DEF ; 
 int /*<<< orphan*/  Q_NEWS ; 
 int /*<<< orphan*/  Q_WATCHCAT ; 

qtype get_qtype (char *qname) {
  if (qname[0] == 'w' && qname[1] == '_') {
    return Q_WATCHCAT;
  }
  if (qname[0] == 'n' && qname[1] == '_') {
    return Q_NEWS;
  }
  return Q_DEF;
}