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
struct hostent {int /*<<< orphan*/  h_name; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  NG_HCI_BDADDR_ANY ; 
 struct hostent* bt_gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
bdaddrpr(bdaddr_t const *ba)
{
	extern int	 numeric_bdaddr;
	static char	 str[24];
	struct hostent	*he = NULL;

	if (memcmp(ba, NG_HCI_BDADDR_ANY, sizeof(*ba)) == 0) {
		str[0] = '*';
		str[1] = 0;

		return (str);
	}

	if (!numeric_bdaddr &&
	    (he = bt_gethostbyaddr((char *)ba, sizeof(*ba), AF_BLUETOOTH)) != NULL) {
		strlcpy(str, he->h_name, sizeof(str));

		return (str);
	}

	bt_ntoa(ba, str);

	return (str);
}