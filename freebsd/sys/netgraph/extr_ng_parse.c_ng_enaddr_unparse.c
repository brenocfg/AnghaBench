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
typedef  int u_char ;
struct ng_parse_type {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ ETHER_ADDR_LEN ; 
 int snprintf (char*,int,char*,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static int
ng_enaddr_unparse(const struct ng_parse_type *type,
	const u_char *data, int *off, char *cbuf, int cbuflen)
{
	int len;

	len = snprintf(cbuf, cbuflen, "%02x:%02x:%02x:%02x:%02x:%02x",
	    data[*off], data[*off + 1], data[*off + 2],
	    data[*off + 3], data[*off + 4], data[*off + 5]);
	if (len >= cbuflen)
		return (ERANGE);
	*off += ETHER_ADDR_LEN;
	return (0);
}