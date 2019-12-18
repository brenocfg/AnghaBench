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
typedef  enum gas_query_result { ____Placeholder_gas_query_result } gas_query_result ;

/* Variables and functions */
#define  GAS_QUERY_DELETED_AT_DEINIT 134 
#define  GAS_QUERY_FAILURE 133 
#define  GAS_QUERY_INTERNAL_ERROR 132 
#define  GAS_QUERY_PEER_ERROR 131 
#define  GAS_QUERY_STOPPED 130 
#define  GAS_QUERY_SUCCESS 129 
#define  GAS_QUERY_TIMEOUT 128 

__attribute__((used)) static const char * gas_result_txt(enum gas_query_result result)
{
	switch (result) {
	case GAS_QUERY_SUCCESS:
		return "SUCCESS";
	case GAS_QUERY_FAILURE:
		return "FAILURE";
	case GAS_QUERY_TIMEOUT:
		return "TIMEOUT";
	case GAS_QUERY_PEER_ERROR:
		return "PEER_ERROR";
	case GAS_QUERY_INTERNAL_ERROR:
		return "INTERNAL_ERROR";
	case GAS_QUERY_STOPPED:
		return "STOPPED";
	case GAS_QUERY_DELETED_AT_DEINIT:
		return "DELETED_AT_DEINIT";
	}

	return "N/A";
}