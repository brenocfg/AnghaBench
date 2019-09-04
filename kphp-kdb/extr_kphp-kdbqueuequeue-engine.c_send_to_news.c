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
 int /*<<< orphan*/  news_conn ; 
 int send_to (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int send_to_news (char *query, int query_len) {
//  fprintf (stderr, "OPPA %p", query);
//  fprintf (stderr, "SEND TO NEWS [%s], %d\n", query, query_len);
  return send_to (news_conn, query, query_len, 0);
}