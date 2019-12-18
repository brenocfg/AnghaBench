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
struct sockaddr_un {int sun_family; int sun_len; int* sun_path; } ;
typedef  size_t socklen_t ;

/* Variables and functions */
 size_t OF ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print(const char *msg, struct sockaddr_un *addr, socklen_t len)
{
	size_t i;

	printf("%s: client socket length: %zu\n", msg, (size_t)len);
	printf("%s: client family %d\n", msg, addr->sun_family);
#ifdef BSD4_4
	printf("%s: client len %d\n", msg, addr->sun_len);
#endif
	printf("%s: socket name: ", msg);
	for (i = 0; i < len - OF; i++) {
		int ch = addr->sun_path[i];
		if (ch < ' ' || '~' < ch)
			printf("\\x%02x", ch);
		else
			printf("%c", ch);
	}
	printf("\n");
}