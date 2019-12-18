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
struct url {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CHECK_FLAG (char) ; 
 int /*<<< orphan*/  ftp_get_proxy (struct url*,char const*) ; 
 int /*<<< orphan*/ * ftp_request (struct url*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

FILE *
fetchPutFTP(struct url *url, const char *flags)
{
	return (ftp_request(url, CHECK_FLAG('a') ? "APPE" : "STOR", NULL,
	    ftp_get_proxy(url, flags), flags));
}