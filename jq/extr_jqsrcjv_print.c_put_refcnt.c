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
struct dtoa_context {int dummy; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int JVP_DTOA_FMT_MAX_LEN ; 
 int /*<<< orphan*/  jvp_dtoa_fmt (struct dtoa_context*,char*,int) ; 
 int /*<<< orphan*/  put_char (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void put_refcnt(struct dtoa_context* C, int refcnt, FILE *F, jv* S, int T){
  char buf[JVP_DTOA_FMT_MAX_LEN];
  put_char(' ', F, S, T);
  put_char('(', F, S, T);
  put_str(jvp_dtoa_fmt(C, buf, refcnt), F, S, T);
  put_char(')', F, S, T);
}