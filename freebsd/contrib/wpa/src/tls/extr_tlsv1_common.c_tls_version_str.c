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
typedef  int u16 ;

/* Variables and functions */
#define  TLS_VERSION_1 130 
#define  TLS_VERSION_1_1 129 
#define  TLS_VERSION_1_2 128 

const char * tls_version_str(u16 ver)
{
	switch (ver) {
	case TLS_VERSION_1:
		return "1.0";
	case TLS_VERSION_1_1:
		return "1.1";
	case TLS_VERSION_1_2:
		return "1.2";
	}

	return "?";
}