void
optionstatus(void)
{
    int i;
    extern char will_wont_resp[], do_dont_resp[];

    for (i = 0; i < 256; i++) {
	if (do_dont_resp[i]) {
	    if (TELOPT_OK(i))
		printf("resp DO_DONT %s: %d\n", TELOPT(i), do_dont_resp[i]);
	    else if (TELCMD_OK(i))
		printf("resp DO_DONT %s: %d\n", TELCMD(i), do_dont_resp[i]);
	    else
		printf("resp DO_DONT %d: %d\n", i,
				do_dont_resp[i]);
	    if (my_want_state_is_do(i)) {
		if (TELOPT_OK(i))
		    printf("want DO   %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want DO   %s\n", TELCMD(i));
		else
		    printf("want DO   %d\n", i);
	    } else {
		if (TELOPT_OK(i))
		    printf("want DONT %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want DONT %s\n", TELCMD(i));
		else
		    printf("want DONT %d\n", i);
	    }
	} else {
	    if (my_state_is_do(i)) {
		if (TELOPT_OK(i))
		    printf("     DO   %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("     DO   %s\n", TELCMD(i));
		else
		    printf("     DO   %d\n", i);
	    }
	}
	if (will_wont_resp[i]) {
	    if (TELOPT_OK(i))
		printf("resp WILL_WONT %s: %d\n", TELOPT(i), will_wont_resp[i]);
	    else if (TELCMD_OK(i))
		printf("resp WILL_WONT %s: %d\n", TELCMD(i), will_wont_resp[i]);
	    else
		printf("resp WILL_WONT %d: %d\n",
				i, will_wont_resp[i]);
	    if (my_want_state_is_will(i)) {
		if (TELOPT_OK(i))
		    printf("want WILL %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want WILL %s\n", TELCMD(i));
		else
		    printf("want WILL %d\n", i);
	    } else {
		if (TELOPT_OK(i))
		    printf("want WONT %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("want WONT %s\n", TELCMD(i));
		else
		    printf("want WONT %d\n", i);
	    }
	} else {
	    if (my_state_is_will(i)) {
		if (TELOPT_OK(i))
		    printf("     WILL %s\n", TELOPT(i));
		else if (TELCMD_OK(i))
		    printf("     WILL %s\n", TELCMD(i));
		else
		    printf("     WILL %d\n", i);
	    }
	}
    }

}