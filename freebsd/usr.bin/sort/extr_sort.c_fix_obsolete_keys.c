void
fix_obsolete_keys(int *argc, char **argv)
{
	char sopt[129];

	for (int i = 1; i < *argc; i++) {
		char *arg1;

		arg1 = argv[i];

		if (strlen(arg1) > 1 && arg1[0] == '+') {
			int c1, f1;
			char sopts1[128];

			sopts1[0] = 0;
			c1 = f1 = 0;

			if (parse_pos_obs(arg1 + 1, &f1, &c1, sopts1) < 0)
				continue;
			else {
				f1 += 1;
				c1 += 1;
				if (i + 1 < *argc) {
					char *arg2 = argv[i + 1];

					if (strlen(arg2) > 1 &&
					    arg2[0] == '-') {
						int c2, f2;
						char sopts2[128];

						sopts2[0] = 0;
						c2 = f2 = 0;

						if (parse_pos_obs(arg2 + 1,
						    &f2, &c2, sopts2) >= 0) {
							if (c2 > 0)
								f2 += 1;
							sprintf(sopt, "-k%d.%d%s,%d.%d%s",
							    f1, c1, sopts1, f2, c2, sopts2);
							argv[i] = sort_strdup(sopt);
							for (int j = i + 1; j + 1 < *argc; j++)
								argv[j] = argv[j + 1];
							*argc -= 1;
							continue;
						}
					}
				}
				sprintf(sopt, "-k%d.%d%s", f1, c1, sopts1);
				argv[i] = sort_strdup(sopt);
			}
		}
	}
}