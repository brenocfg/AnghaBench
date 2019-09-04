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
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 scalar_t__ Q_NEWS ; 
 scalar_t__ get_qtype (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 

ll get_news_s_id (char *s) {
  ll id = 0;
  if (get_qtype (s) == Q_NEWS) {
    sscanf (s + 2 + (s[2] == '_'), "%lld", &id);
    if (s[2] == '_') {
      id = -id;
    }
  }
  return id;
}