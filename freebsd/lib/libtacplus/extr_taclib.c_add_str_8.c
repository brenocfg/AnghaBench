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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct tac_handle {int dummy; } ;
struct clnt_str {int dummy; } ;

/* Variables and functions */
 int add_str_16 (struct tac_handle*,int*,struct clnt_str*) ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*) ; 
 int ntohs (int) ; 

__attribute__((used)) static int
add_str_8(struct tac_handle *h, u_int8_t *fld, struct clnt_str *cs)
{
	u_int16_t len;

	if (add_str_16(h, &len, cs) == -1)
		return -1;
	len = ntohs(len);
	if (len > 0xff) {
		generr(h, "Field too long");
		return -1;
	}
	*fld = len;
	return 0;
}